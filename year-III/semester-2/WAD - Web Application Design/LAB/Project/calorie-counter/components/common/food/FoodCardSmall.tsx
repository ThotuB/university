import { FoodDto } from "types/food";

interface FoodCardSmallProps {
    food: FoodDto;
}

export default function FoodCardSmall({ food }: FoodCardSmallProps) {
    const calories = food.foodNutrients.find(n => n.nutrientId === 1008)?.value || "0"
    
    return (
        <div className="py-1 px-2 flex gap-3">
            <div className="text-purple-500 font-bold">
                {food.description}
            </div>
            <div className="text-sm text-gray-700 pt-1">
                {food.brandOwner}
            </div>
            <div className="font-mono font-bold text-purple-400">
                {calories}
            </div>
        </div>
    )
}
