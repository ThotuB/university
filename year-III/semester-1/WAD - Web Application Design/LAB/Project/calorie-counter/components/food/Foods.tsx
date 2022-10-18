import { FoodDto, NutrientDto } from 'types/food';
import Food from './Food';

interface FoodListProps {
    items: FoodDto[]
}

export default function FoodList({ items }: FoodListProps) {
    return (
        <div className='flex flex-col gap-4 mb-4 w-full'>
            {items.map((item) => {
                const { fdcId, brandName, brandOwner, description, foodNutrients, servingSize, servingSizeUnit } = item;
                const rating = 3;

                const macros = {
                    calories: findNutrientValue(foodNutrients, 1008),
                    protein: findNutrientValue(foodNutrients, 1003),
                    fat: findNutrientValue(foodNutrients, 1004),
                    carbs: findNutrientValue(foodNutrients, 1005)
                };
                const calories = Math.round(macros.calories / 100 * servingSize);
                const serving = Math.round(servingSize);

                return (
                    <Food
                        key={fdcId}
                        id={fdcId}
                        description={description}
                        macros={macros}
                        calories={calories}
                        company={brandOwner}
                        name={brandName}
                        rating={rating}
                        servingSize={serving}
                        servingUnit={servingSizeUnit}
                    />
                );
            })}
        </div>
    );
}

function findNutrientValue(nutrients: NutrientDto[], id: number) {
    const nutrient = nutrients.find(nutrient => nutrient.nutrientId === id)
    return nutrient ? nutrient.value : 0;
}