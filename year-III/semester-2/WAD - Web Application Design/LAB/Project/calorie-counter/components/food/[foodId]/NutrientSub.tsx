import Nutrient from './Nutrient';
import { NutrientProps } from './Nutrient';

export default function NutrientSub({ label, quantity, unit }: NutrientProps) {
    return (
        <div className="flex text-gray-800">
            <div className="w-1/12 flex justify-center">
                <div className="bg-gray-700 w-2 h-8 rounded-t-full rounded-bl-full" />
                <div className="bg-gray-700 w-7/12 h-2 self-center rounded-r-full" />
            </div>
            <div className="bg-purple-200 w-full rounded-xl">
                <Nutrient label={label} quantity={quantity} unit={unit} />
            </div>
        </div>
    )
}