function Button(props) {
    const { onClick, className } = props

    return (
        <button className={`${className} text-sm font-bold text-white duration-100 transform transition-all rounded-md hover:bg-gray-800`}
            onClick={onClick}>
            {props.children}
        </button>
    )
}

export default Button