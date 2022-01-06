interface TextFieldProps {
    children?: never;
    className?: string;
    type?: string;
    label?: string;
    placeholder?: string;
    required?: boolean;
    error?: boolean;
    errorText?: string;
    value?: string;
    maxLength?: number;
    onChange?: (event: React.ChangeEvent<HTMLInputElement>) => void;
}

export default function TextField({ className, type, label, placeholder, required, error, errorText, value, maxLength, onChange }: TextFieldProps) {
    const labelTextColor = error ? 'text-red-400' : 'text-gray-800';
    const inputRingColor = error ? 'ring ring-red-300' : '';

    return (
        <div className="w-full flex flex-col gap-2">
            {label && <div className={`text-sm ${labelTextColor}`}>
                {label} {required ? '*' : ''}
            </div>}
            <div className="relative">
                <div className="absolute text-red-400 pointer-events-none font-semibold right-0 pr-4 py-2 text-right">
                    {error && errorText}
                </div>
                <input className={`${className} w-full px-4 py-2 text-gray-700 bg-white border ${inputRingColor} rounded-md focus:outline-none focus:ring focus:ring-purple-300`}
                    type={type}
                    placeholder={placeholder}
                    value={value}
                    maxLength={maxLength}
                    onChange={onChange}
                />
            </div>
        </div>
    );
}