import Router from 'next/router';
interface MenuItemProps {
    icon: React.ReactNode;
    label: string;
    onClick: () => void;
}

export default function MenuItem({ icon, label, onClick }: MenuItemProps) {
    return (
        <div className="flex items-center w-full cursor-pointer p-3 text-sm text-gray-600 capitalize transition-colors duration-200 transform hover:bg-gray-100"
            onClick={onClick}
        >
            {icon}
            <div className='mx-2'>
                {label}
            </div>
        </div>
    );
}