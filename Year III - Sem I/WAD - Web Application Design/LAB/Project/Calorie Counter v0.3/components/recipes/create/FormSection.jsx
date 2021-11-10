function FormSection(props) {
    const { children } = props;
    const [ label, field, description ] = children;

    const descElem = description ?
        <div className="mt-2 text-sm text-gray-500">
            {description}
        </div> :
        undefined;

    return (
        <div>
            <div className="text-sm font-semibold text-gray-800 mb-1">
                {label}
            </div>
            {field}
            {descElem}
        </div>
    )
}

export default FormSection;