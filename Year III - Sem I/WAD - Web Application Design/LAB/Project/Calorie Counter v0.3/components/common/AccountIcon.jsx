function Account(props) {
    const { name, image } = props;
    const initial = name.charAt(0).toUpperCase();

    return (
        <button className="flex items-center gap-2">
            <div className="w-8 h-8 border-2 text-center border-gray-500 rounded-full hover:rounded-xl">
                {initial}
            </div>
            <div className="text-md font-semibold text-gray-700">
                {name}
            </div>
        </button>
    );
}

export default Account;