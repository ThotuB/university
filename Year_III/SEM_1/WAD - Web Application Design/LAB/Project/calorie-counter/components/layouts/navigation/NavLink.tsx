import Router from 'next/router';

interface NavLinkProps {
    href: string;
    label: string;
}

export default function NavLink({ href, label }: NavLinkProps) {
    return (
        <button className="px-3 py-2 rounded-md text-gray-700 transition-colors duration-200 transform hover:bg-purple-400 font-bold"
            onClick={() => Router.push(href)}
        >
            {label}
        </button>
    );
}