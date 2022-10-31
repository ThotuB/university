x=0:0.1:5;
f=(5-x)/3.2;

Uce=[1.92];
Ic=[0.95];

plot(x, f,'b');
hold on;
scatter(Uce, Ic, 100, 'xk');
ylabel('Ic[mA]');
xlabel('Uce[V]');

hold on
for i=1:1
    plot([Uce(i), Uce(i)], [0, Ic(i)], 'k--')
end
for i=1:1
    plot([0, Uce(i)], [Ic(i), Ic(i)], 'k--')
end

text(Uce(1)+0.1,Ic(1)+0.1,'Q1');

set(gcf,'position',[1000,700, 800, 400]);

set(gca,'xtick',[0:0.5:6])
set(gca,'ytick',[0:0.2:1.6])
ylim([0 1.7])
xlim([0 6])

grid on;