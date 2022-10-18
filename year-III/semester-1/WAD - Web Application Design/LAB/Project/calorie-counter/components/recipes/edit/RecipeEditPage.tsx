import Router from "next/router";
import { updateRecipe } from "services/recipe";
import { RecipeDto } from "types/recipe";
import EditForm from "./EditForm";

interface RecipeEditPageProps {
    recipe: RecipeDto;
}

export default function RecipeEditPage({ recipe }: RecipeEditPageProps) {
    const handleEdit = async (recipe: RecipeDto) => {
        await updateRecipe(recipe)

        Router.push('/recipes');
    }

    return (
        <EditForm recipe={recipe} onEdit={handleEdit}/>
    );
}