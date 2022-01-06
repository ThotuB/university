import Nav from './Nav';

interface LayoutProps {
    children: React.ReactNode;
}

export default function Layout({ children }: LayoutProps) {
    return (
        <div className="w-screen h-full min-h-screen bg-gray-50">
            <Nav />
            <main className="w-11/12 py-4 max-w-5xl m-auto">
                {children}
            </main>
        </div>
    );
}