import InfoField from "../form/InfoFields";
import IngredientField from "../form/IngredientField";
import StepField from "../form/StepField";
import Divider from "components/common/Divider";
import { useState } from "react";
import Button from "components/common/Button";
import { IRecipeIngredient, RecipeDto, IRecipeInfo } from "types/recipe";

interface FormProps {
    recipe: RecipeDto;
    onEdit: (recipe: RecipeDto) => void;
}

export default ({ recipe: {id, name, description, image, ingredients: recipeIngredients, steps: recipeSteps}, onEdit }: FormProps) => {
    const [info, setInfo] = useState<IRecipeInfo>({name: name, description: description, image: image});
    const [ingredients, setIngredients] = useState<IRecipeIngredient[]>(recipeIngredients);
    const [steps, setSteps] = useState<string[]>(recipeSteps);

    const handleEdit = () => {
        const recipe = {
            id: id,
            ...info,
            ingredients,
            steps
        };
        onEdit(recipe);
    }

    return (
        <div className="w-full bg-gray-100 rounded-md border p-4 flex flex-col gap-6">
            <InfoField recipeInfo={info} onSave={setInfo} />

            <Divider />

            <IngredientField recipeIngredients={ingredients} onSave={setIngredients} />

            <Divider />

            <StepField recipeSteps={steps} onSave={setSteps} />

            <Divider />

            <Button className="rounded-2xl"
                onClick={handleEdit}
            >
                SAVE EDIT
            </Button>
        </div>
    );
}