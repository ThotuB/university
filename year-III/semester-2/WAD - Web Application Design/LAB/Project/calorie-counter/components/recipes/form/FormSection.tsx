interface SectionProps {
    label: string;
    children: React.ReactNode;
    required?: boolean;
    description?: string;
}

function FormSection({ label, children, required, description }: SectionProps) {
    return (
        <div className="flex flex-col">
            <div className="text-sm font-semibold text-gray-800 mb-1">
                {label} {required && '*'}
            </div>
            <div className="flex flex-col gap-3">
                {children}
            </div>
            {description && (
                <div className="text-gray-600">
                    {description}
                </div>
            )}
        </div>
    )
}

export default FormSection;