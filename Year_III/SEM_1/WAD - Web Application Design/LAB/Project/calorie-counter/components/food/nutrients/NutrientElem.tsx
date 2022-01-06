import Nutrient from './Nutrient';
import { NutrientProps } from './Nutrient';


function NutrientElem({ label, quantity, unit }: NutrientProps) {
    return (
        <div className="bg-purple-300 rounded-xl">
            <Nutrient label={label} quantity={quantity} unit={unit} />
        </div>
    )
}

export default NutrientElem;