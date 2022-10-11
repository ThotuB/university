import RecipeForm from 'components/recipes/create/CreateForm'
import CreateForm from 'components/recipes/create/CreateForm'
import axios from 'axios';
import Router from 'next/router';
import { IRecipe } from 'types/recipe';

export default function RecipeCreatePage() {
    const handleCreate = async (recipe: IRecipe) => {
        await axios.post('/api/recipes', recipe);

        Router.push('/recipes');
    }

    return (
        <CreateForm onCreate={handleCreate} />
    );
}