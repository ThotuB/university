function Button(props) {
    const { name, onClick } = props;

    return (
        <button className="px-3 py-2 text-sm font-bold text-white transition-colors duration-200 transform bg-gray-800 rounded-md hover:bg-purple-400"
            onClick={onClick}
        >
            {name}
            {props.children}
        </button>
    )
}

export default Button;