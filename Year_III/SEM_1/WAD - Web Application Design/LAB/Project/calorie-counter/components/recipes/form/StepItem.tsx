import { MinusIcon } from '@heroicons/react/outline';
import Button from 'components/common/Button'

interface StepItemProps {
    step: string;
    id: number;
    onDelete: () => void;
}

export default function StepItem({ step, id, onDelete }: StepItemProps) {
    return (
        <div className="flex items-center text-sm font-bold text-gray-600">
            <Button className="py-1"
                onClick={() => onDelete()}
            >
                <MinusIcon className='w-5' />
            </Button>
            <div className="pl-4 w-12">
                {id + 1}.
            </div>
            <div className="px-2">
                {step}
            </div>
        </div>
    )
}