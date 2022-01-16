interface AccountIconProps {
    image?: string | null;
    name: string | null;
}

export default ({ image, name }: AccountIconProps) => {
    const initial = name?.charAt(0).toUpperCase();

    return (
        <button className="flex items-center gap-2">
            {image ?
                <img className="w-8 h-8 border-2 border-purple-300 rounded-full hover:rounded-xl" src={image} /> :
                <div className="w-8 h-8 border-2 text-center border-purple-300 rounded-full hover:rounded-xl">
                    {initial}
                </div>
            }
            <div className="text-md font-semibold text-gray-700">
                {name}
            </div>
        </button>
    );
}