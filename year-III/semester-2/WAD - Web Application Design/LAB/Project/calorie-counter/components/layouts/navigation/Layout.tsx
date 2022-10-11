import Nav from './Nav';

interface LayoutProps {
    children: React.ReactNode;
}

export default function Layout({ children }: LayoutProps) {
    return (
        <div className="w-full h-full min-h-screen bg-gray-100">
            <Nav />
            <main className="w-11/12 py-4 max-w-7xl m-auto flex flex-col gap-6 items-center">
                {children}
            </main>
        </div>
    );
}