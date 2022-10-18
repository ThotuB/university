import Layout from 'components/layouts/navigation/Layout'
import RecipeCreatePage from 'components/recipes/create/RecipeCreatePage';

export default function Index() {
    return (
        <Layout>
            <RecipeCreatePage />
        </Layout>
    );
}