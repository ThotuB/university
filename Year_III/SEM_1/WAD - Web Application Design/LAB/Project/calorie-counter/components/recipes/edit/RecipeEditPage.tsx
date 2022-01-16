import axios from "axios";
import Router from "next/router";
import { IRecipe } from "types/recipe";
import EditForm from "./EditForm";

interface RecipeEditPageProps {
    recipe: IRecipe;
}

export default function RecipeEditPage({ recipe }: RecipeEditPageProps) {
    const handleEdit = async (recipe: IRecipe) => {
        await axios.post<IRecipe>('/api/recipes', recipe);

        Router.push('/recipes');
    }

    return (
        <EditForm recipe={recipe} onEdit={handleEdit}/>
    );
}