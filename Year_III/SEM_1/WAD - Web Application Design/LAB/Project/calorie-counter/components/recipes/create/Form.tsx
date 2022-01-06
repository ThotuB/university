import InfoField from "./InfoField";
import IngredientField from "./IngredientField";
import StepField from "./StepField";
import Divider from "components/common/Divider";
import { useState } from "react";
import Button from "components/common/Button";

interface FormProps {
    onCreate: (recipe: Recipe) => void;
}

export interface Recipe extends Info {
    ingredients: Ingredient[];
    steps: Step[];
}

export interface Info {
    name: string;
    description: string;
    image: string;
}

export interface Ingredient {
    id: string;
    name: string;
    quantity: string;
}

export interface Step {
    step: string;
}

function Form({ onCreate }: FormProps) {
    const [info, setInfo] = useState<Info>({} as Info);
    const [ingredients, setIngredients] = useState<Ingredient[]>([] as Ingredient[]);
    const [steps, setSteps] = useState<Step[]>({} as Step[]);

    const handleCreate = () => {
        const recipe = {
            ...info,
            ingredients,
            steps
        };
        onCreate(recipe);
    }

    return (
        <div className="w-full bg-gray-100 rounded-md border p-4 flex flex-col gap-6">
            <InfoField onSave={setInfo} />

            <Divider />

            <IngredientField onSave={setIngredients} />

            <Divider />

            <StepField onSave={setSteps} />

            <Divider />

            <Button className="rounded-2xl"
                onClick={handleCreate}
            >
                CREATE RECIPE
            </Button>
        </div>
    );
}

export default Form;
