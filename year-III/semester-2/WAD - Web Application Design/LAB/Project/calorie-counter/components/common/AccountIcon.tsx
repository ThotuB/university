import Router from "next/router";

interface AccountIconProps {
    image?: string | null;
    name: string | null;
    id: string;
}

export default ({ image, name, id }: AccountIconProps) => {
    const initial = name?.charAt(0).toUpperCase();

    return (
        <button className="flex items-center gap-2"
            onClick={() => Router.push(`/profile/${id}`)}
        >
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