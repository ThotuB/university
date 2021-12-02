function Select(props) {
    const {className, onChange, options, value, theme} = props || {};

    return (
        // <div>
            <select className={className} onChange={(e) => onChange(e)} value={value}>
                {options.map((option, idx) => (
                    <option className={theme} key={idx} value={option.value}>
                        {option.label}
                    </option>
                ))}
            </select>
        // </div>
    );
}

export default Select;