import Food from './Food';

interface Nutrient {
    nutrientId: number;
    value: number;
}

interface Food {
    fdcId: number;
    description: string;
    brandOwner: string;
    brandName: string;
    foodNutrients: Nutrient[];
    servingSize: number;
    servingSizeUnit: string;
}

interface FoodListProps {
    items: Food[]
}

export default function FoodList({ items }: FoodListProps) {
    const food_list = items.map((item) => {
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
    })

    return (
        <div className='flex flex-col gap-4 mb-4'>
            {food_list}
        </div>
    );
}

function findNutrientValue(nutrients: Nutrient[], id: number) {
    const nutrient = nutrients.find(nutrient => nutrient.nutrientId === id)
    return nutrient ? nutrient.value : 0;
}