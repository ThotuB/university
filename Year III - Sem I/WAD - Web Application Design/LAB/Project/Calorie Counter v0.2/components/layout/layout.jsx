import Navigation from './navigation';
import style from './styles/layout.module.css'

function Layout(props) {
    return (
        <div className={style.page}>
            <Navigation />
            <main className={style.main}>
                {props.children}
            </main>
        </div>
    );
}

export default Layout; 