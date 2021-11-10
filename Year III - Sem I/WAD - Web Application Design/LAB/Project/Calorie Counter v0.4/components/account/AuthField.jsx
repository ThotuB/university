function AuthField(props) {
    const { type, children, htmlFor } = props;

    return (
        <div>
            <label htmlFor={htmlFor} className="block text-sm text-gray-800">
                {children}
            </label>
            <input className="block w-full px-4 py-2 mt-2 text-gray-700 bg-white border rounded-md focus:outline-none focus:ring focus:ring-purple-300"
                type={type}
            />
        </div>
    );
}

export default AuthField;
