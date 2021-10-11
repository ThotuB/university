import Navigation from './navigation';

function Layout(props) {
  return (
    <div>
      <Navigation />
      <main>
        {props.children}
      </main>
    </div>
  );
}

export default Layout;