interface TextAreaProps {
    children?: never;
    className?: string;
    label?: string;
    placeholder?: string;
    required?: boolean;
    value?: string;
    onChange?: (event: React.ChangeEvent<HTMLTextAreaElement>) => void;
}

export default function TextArea({ className, label, placeholder, required, value, onChange }: TextAreaProps) {
    return (
        <div className="flex flex-col gap-2">
            {label && <div className="text-sm text-gray-800">
                {label} {required ? '*' : ''}
            </div>}
            <textarea className={`${className} px-4 py-2 text-gray-700 bg-white border rounded-md focus:outline-none focus:ring focus:ring-purple-300`}
                placeholder={placeholder}
                value={value}
                onChange={onChange}
            />
        </div>
    );
}