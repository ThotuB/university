import RecipeForm from 'components/recipes/create/Form'
import Layout from 'components/layouts/navigation/Layout'
import { Recipe } from 'components/recipes/create/Form'
import axios from 'axios';

export default function Index() {
    async function handleCreate(recipe: Recipe) {
        const response = await axios.post<Recipe>('/api/recipe', recipe);

        console.log(response.data);
    }

    return (
        <Layout>
            <RecipeForm onCreate={handleCreate} />
        </Layout>
    );
}