import InfoField from "../form/InfoFields";
import IngredientField from "../form/IngredientField";
import StepField from "../form/StepField";
import Divider from "components/common/Divider";
import { useState } from "react";
import Button from "components/common/Button";
import { useUser } from "contexts/UserContext";
import { RecipeDto, IRecipeInfo, IRecipeIngredient } from "types/recipe";

interface FormProps {
    onCreate: (recipe: RecipeDto) => void;
}

export default ({ onCreate }: FormProps) => {
    const [info, setInfo] = useState<IRecipeInfo>({
        name: "",
        description: "",
        image: ""
    });
    const [ingredients, setIngredients] = useState<IRecipeIngredient[]>([]);
    const [steps, setSteps] = useState<string[]>([]);

    const { user } = useUser();

    const handleCreate = () => {
        const recipe: RecipeDto = {
            ...info,
            ingredients,
            steps,
            user: {
                id: user?.uid,
                name: user?.displayName,
                image: user?.photoURL
            }
        };
        onCreate(recipe);
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