
import Navigation from './Nav';

function Layout(props) {
    return (
        <div className="w-screen h-full min-h-screen bg-gray-50">
            <Navigation />
            <main className="w-11/12 max-w-5xl m-auto">
                {props.children}
            </main>
        </div>
    );
}

export default Layout; 