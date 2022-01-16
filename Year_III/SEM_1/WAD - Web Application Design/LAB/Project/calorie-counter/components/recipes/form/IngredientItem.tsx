import { MinusIcon } from '@heroicons/react/outline';
import Button from 'components/common/Button'
import { IRecipeIngredient } from 'types/recipe';

interface IngredientItemProps {
    ingredient: IRecipeIngredient;
    onDelete: () => void;
}

export default function IngredientItem({ ingredient: { id, name, quantity }, onDelete }: IngredientItemProps) {
    return (
        <div className="flex items-center text-sm font-bold text-gray-600">
            <Button className="py-1"
                onClick={() => onDelete()}
            >
                <MinusIcon className='w-5' />
            </Button>
            <div className="w-1/2 px-4">
                {name}
            </div>
            <div className="w-1/2 text-right px-4">
                {quantity}
            </div>
        </div>
    )
}