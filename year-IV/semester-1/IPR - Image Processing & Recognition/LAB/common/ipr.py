import plotly.graph_objects as go
import plotly.express as px
from termcolor import colored
from torch import optim
from torch.optim.optimizer import Optimizer
from typing import Callable
from torch import Tensor
from torch import device
import torch
from torch import nn

from torchvision import transforms
from torchvision.datasets import FashionMNIST, MNIST
from torch.utils.data import DataLoader, random_split, Subset
from torch import Generator


def load_data(Mnist: MNIST, batch_size: int, split: list[int, int], resize: int | None = None) -> tuple[DataLoader, DataLoader, DataLoader]:
    """Download a dataset and then load it into memory."""
    trans: list[transforms.ToTensor] = [transforms.ToTensor()]
    if resize:
        trans.insert(0, transforms.Resize(resize))

    transform: transforms.Compose = transforms.Compose(trans)

    mnist_train: MNIST = Mnist(
        root="../data", train=True, transform=transform, download=True)
    mnist_test: MNIST = Mnist(
        root="../data", train=False, transform=transform, download=True)

    mnist_train, mnist_val = random_split(
        mnist_train, split, generator=Generator().manual_seed(42))

    return (
        DataLoader(mnist_train, batch_size, shuffle=True, num_workers=2),
        DataLoader(mnist_val, batch_size, shuffle=False, num_workers=2),
        DataLoader(mnist_test, batch_size, shuffle=False, num_workers=2)
    )


def try_gpu(i=0) -> device:
    """Return gpu(i) if exists, otherwise return cpu()."""
    if torch.cuda.device_count() >= i + 1:
        return torch.device(f'cuda:{i}')
    return torch.device('cpu')


def evaluate_accuracy(
        net: nn.Module,
        data_iter: DataLoader,
        loss: Callable[..., Tensor],
        device: device) -> tuple[float, float]:
    """Compute the accuracy for a model on a dataset."""
    net.eval()  # Set the model to evaluation mode

    total_loss: int = 0
    total_hits:  int = 0
    total_samples: int = 0

    with torch.no_grad():
        for X, y in data_iter:
            X, y = X.to(device), y.to(device)
            y_hat = net(X)

            l = loss(y_hat, y)

            total_loss += float(l)
            total_hits += sum(net(X).argmax(axis=1).type(y.dtype) == y)
            total_samples += y.numel()

    return total_loss / len(data_iter), total_hits / total_samples * 100


def train(
        net: nn.Module,
        train_iter: DataLoader,
        val_iter: DataLoader,
        num_epochs: int,
        learning_rate: float,
        loss: Callable[..., Tensor],
        optimizer: Optimizer,
        device) -> tuple[list[float], list[float], list[float], list[float]]:
    """Train a model."""

    def train_epoch() -> tuple[float, float]:
        # Set the model to training mode
        net.train()

        # Sum of training loss, sum of training correct predictions, no. of examples
        total_loss: int = 0
        total_hits: int = 0
        total_samples: int = 0

        for X, y in train_iter:
            # Compute gradients and update parameters
            X, y = X.to(device), y.to(device)
            y_hat = net(X)

            l = loss(y_hat, y)
            # Using PyTorch built-in optimizer & loss criterion
            optimizer.zero_grad()
            l.backward()
            optimizer.step()

            total_loss += float(l)
            total_hits += sum(y_hat.argmax(axis=1).type(y.dtype) == y)
            total_samples += y.numel()

        # Return training loss and training accuracy
        return total_loss / len(train_iter), total_hits / total_samples * 100

    def print_epoch_summary(epoch: int, train_loss: float, train_acc: float, val_loss: float, val_acc: float, last_values: tuple[float, float, float, float]):
        def diff_color(diff: float, is_pos: bool) -> str:
            if (diff > 0.0 and is_pos) or (diff < 0.0 and not is_pos):
                return "green"
            return "red"

        if epoch == 0:
            print(
                f'{epoch + 1:5} | {train_loss:12.2f} | {train_acc:13.2f}% | {val_loss:15.2f} | {val_acc:18.2f}%')
        else:
            train_loss_diff = train_loss - last_values[0]
            train_acc_diff = train_acc - last_values[1]
            val_loss_diff = val_loss - last_values[2]
            val_acc_diff = val_acc - last_values[3]
            print(f'{epoch + 1:5} | ({colored(f"{train_loss_diff:+3.2f}", diff_color(train_loss_diff, False))}) {train_loss:4.2f} ', end='')
            print(
                f'| ({colored(f"{train_acc_diff:+3.2f}", diff_color(train_acc_diff, True))}) {train_acc:5.2f}% ', end='')
            print(
                f'|    ({colored(f"{val_loss_diff:+3.2f}", diff_color(val_loss_diff, False))}) {val_loss:3.2f} ', end='')
            print(
                f'|      ({colored(f"{val_acc_diff:+3.2f}", diff_color(val_acc_diff, True))}) {val_acc:5.2f}%')

    train_loss_all: list[float] = []
    train_acc_all: list[float] = []
    val_loss_all: list[float] = []
    val_acc_all: list[float] = []

    def init_weights(m):
        if type(m) == nn.Linear or type(m) == nn.Conv2d:
            nn.init.xavier_uniform_(m.weight)

    net.apply(init_weights)

    print('Training on', device)
    net.to(device)

    optimizer = torch.optim.SGD(net.parameters(), lr=learning_rate)
    loss = nn.CrossEntropyLoss()

    last_values: tuple[float, float, float, float] = (0.0, 0.0, 0.0, 0.0)
    print(f'Epoch |   Train Loss | Train Accuracy | Validation Loss | Validation Accuracy')
    for epoch in range(num_epochs):
        train_loss, train_acc = train_epoch()
        train_loss_all.append(train_loss)
        train_acc_all.append(train_acc)

        val_loss, val_acc = evaluate_accuracy(net, val_iter, loss, device)
        val_loss_all.append(val_loss)
        val_acc_all.append(val_acc)

        print_epoch_summary(epoch, train_loss, train_acc,
                            val_loss, val_acc, last_values)
        last_values = (train_loss, train_acc, val_loss, val_acc)

    return train_loss_all, train_acc_all, val_loss_all, val_acc_all


def plot_loss(train_loss_all: list[float], val_loss_all: list[float]):
    epochs = list(range(1, len(train_loss_all) + 1))
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=epochs, y=train_loss_all,
                  name='Training loss', line=dict(width=4)))
    fig.add_trace(go.Scatter(x=epochs, y=val_loss_all,
                  name='Validation loss', line=dict(width=4)))
    fig.update_layout(
        title='Training and validation loss',
        paper_bgcolor='rgba(0,0,0,0)',
        plot_bgcolor='rgba(0,0,0,0)',
        font={
            'size': 18,
            'color': 'white'
        },
        xaxis={
            'title': 'Epochs',
        },
        yaxis={
            'title': 'Loss',
        })
    fig.show()


def plot_accuracy(train_acc_all: list[float], val_acc_all: list[float]):
    epochs = list(range(1, len(train_acc_all) + 1))
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=epochs, y=train_acc_all,
                  name='Training accuracy', line=dict(width=4)))
    fig.add_trace(go.Scatter(x=epochs, y=val_acc_all,
                  name='Validation accuracy', line=dict(width=4)))
    fig.update_layout(
        title='Training and validation accuracy',
        paper_bgcolor='rgba(0,0,0,0)',
        plot_bgcolor='rgba(0,0,0,0)',
        font={
            'size': 18,
            'color': 'white'
        },
        xaxis={
            'title': 'Epochs',
        },
        yaxis={
            'title': 'Accuracy',
        }
    )
    fig.show()


def init_weights(std: float):
    def init(m: nn.Module | nn.Linear):
        if type(m) == nn.Linear:
            nn.init.normal_(m.weight, std=std)

    return init


def test_net(net: nn.Module, x: torch.Tensor):
    for layer in net:
        x: Tensor = layer(x)
        print(f'{layer.__class__.__name__: <15}\t->\t{x.shape}')
