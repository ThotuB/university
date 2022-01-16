import InfoField from "../form/InfoFields";
import IngredientField from "../form/IngredientField";
import StepField from "../form/StepField";
import Divider from "components/common/Divider";
import { useState } from "react";
import Button from "components/common/Button";
import { IRecipeIngredient, IRecipe, IRecipeInfo } from "types/recipe";

interface FormProps {
    recipe : IRecipe;
    onEdit: (recipe: IRecipe) => void;
}

export default ({ recipe, onEdit }: FormProps) => {
    const [info, setInfo] = useState<IRecipeInfo>({name: recipe.name, description: recipe.description, image: recipe.image});
    const [ingredients, setIngredients] = useState<IRecipeIngredient[]>(recipe.ingredients);
    const [steps, setSteps] = useState<string[]>(recipe.steps);

    const handleCreate = () => {
        
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
                onClick={handleCreate}
            >
                SAVE EDIT
            </Button>
        </div>
    );
}