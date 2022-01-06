import Button from 'components/common/Button'

interface FormCardProps {
    children: React.ReactNode;
    name: string;
    description: string;
    onSave: () => void;
}

function FormCard({ children, name, description, onSave }: FormCardProps) {
    return (
        <div className="w-full rounded-2xl flex">
            <div className="w-1/3">
                <div className="font-semibold text-lg">
                    {name}
                </div>
                <div className="text-gray-500">
                    {description}
                </div>
            </div>
            <div className="w-2/3 bg-white border overflow-x-hidden overflow-y-visible rounded-lg shadow-md h-full flex flex-col justify-between">
                <div className="p-4 flex flex-col gap-6">
                    {children}
                </div>
                <div className="bg-gray-50 px-5 py-3 text-right">
                    <Button className='px-4'
                        onClick={onSave}
                    >
                        Save
                    </Button>
                </div>
            </div>
        </div>
    );
}

export default FormCard;