import Router from 'next/router';
interface MenuItemProps {
    href: string;
    icon: React.ReactNode;
    label: string;
}

export default function MenuItem({ href, icon, label }: MenuItemProps) {
    return (
        <div className="flex items-center w-full cursor-pointer p-3 text-sm text-gray-600 capitalize transition-colors duration-200 transform hover:bg-gray-100"
            onClick={() => Router.push(href)}
        >
            {icon}
            <div className='mx-2'>
                {label}
            </div>
        </div>
    );
}