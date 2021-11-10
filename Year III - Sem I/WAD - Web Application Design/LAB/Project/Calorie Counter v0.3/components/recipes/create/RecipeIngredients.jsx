import FormCard from "./FormCard";
import FormSection from "./FormSection";
import { Plus, Minus } from '../../svg/Heroicons';
import { useState } from "react";

function RecipeIngredients() {
    const [ingredients, setIngredients] = useState([]);

    const addIngredient = (ingredient) => {
        ingredients.push(ingredient);
        setIngredients(ingredients);
    }

    const removeIngredient = (index) => {
        ingredients.splice(index, 1);
        setIngredients(ingredients);
    }

    const ingredientsList = ingredients.map((ingredient, index) => {
        return RecipeIngredient(ingredient, index, removeIngredient);
    })

    return (
        <FormCard name="Ingredients" description="Enter the ingredients">
            <FormSection>
                Add Ingredient *
                <div className="flex gap-1 rounded-xl border-4 border-purple-300 bg-purple-300">
                    <button className="px-3 pl-4 rounded-l-md text-white
                                    hover:ring hover:ring-gray-800 hover:bg-gray-800"
                            onClick={() => addIngredient("Ingredient")}
                    >
                        <Plus />
                    </button>
                    <input
                        className="w-full rounded-r-md py-1 px-2 outline-none 
                                    focus:ring focus:ring-purple-500"
                        placeholder="Burgir"
                    />
                </div>
                <div className="flex flex-col gap-1">
                    {ingredientsList}
                </div>
            </FormSection>
        </FormCard>
    )
}

export default RecipeIngredients;

function RecipeIngredient(ingredientName, index, fn) {
    return (
        <div key={index} className="flex gap-1 rounded-xl border-4 border-purple-300 bg-purple-300">
            <button className="px-3 pl-4 rounded-l-md text-white
                            hover:ring hover:ring-gray-800 hover:bg-gray-800"
                onClick={() => fn(index)}
            >
                <Minus />
            </button>
            <div className="w-full rounded-r-md py-1 px-2 font-bold">
                {ingredientName}
            </div>
        </div>
    )
}