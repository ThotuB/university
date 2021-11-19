import { Minus } from '../../svg/Heroicons'
import Button from '../../common/Button2'

function IngredientList(props) {
    const { ingredients, removeIngredient } = props;

    return (
        <div className="flex flex-col gap-1 rounded-xl bg-purple-200">
            {ingredients.map((ingredient, index) => (
                <div key={index} className="flex items-center py-1 text-sm font-bold text-gray-600">
                    <Button className="px-3 pl-4"
                        onClick={() => removeIngredient(index)}
                    >
                        <Minus />
                    </Button>
                    <div className="w-1/2 px-4">
                        {ingredient.name}
                    </div>
                    <div className="w-1/2 text-right px-4">
                        {ingredient.quantity} {ingredient.unit}
                    </div>
                </div>
            ))}
        </div>
    )
}

export default IngredientList