import Loading from 'components/common/Loading';
import Pagination from 'components/common/Pagination';
import { useUser } from 'contexts/UserContext';
import { useEffect, useState } from 'react';
import { deleteRecipe, getRecipes, updateRecipe } from 'services/recipe';
import { RecipeSummaryDto } from 'types/recipe';
import Recipes from './RecipeList';

export default function RecipesPage() {
    const [recipes, setRecipes] = useState<RecipeSummaryDto[]>([])
    const [page, setPage] = useState(1)
    const [count, setCount] = useState(0)
    const [loading, setLoading] = useState(false)

    const { admin } = useUser();

    useEffect(() => {
        setLoading(true)
        getRecipes(page, 10)
            .then(res => {
                setRecipes(res.data.recipes)
                setCount(res.data.pages)
                setLoading(false)
            })
            .catch(err => {
                console.log(err)
            })

    }, [page])

    const handleDeleteRecipe = async (id: string) => {
        await deleteRecipe(id)
        setRecipes(recipes.filter(recipe => recipe.id !== id))
    }

    const handleApprove = async (id: string, approval: boolean) => {
        await updateRecipe({ id, approved: approval })
        setRecipes(recipes.map(recipe => recipe.id === id ? { ...recipe, approved: approval } : recipe))
    }

    return (
        <div className="flex flex-col gap-6 max-w-3xl">
            <div className="flex flex-col gap-6 w-full items-center">
                {loading ?
                    <Loading /> :
                    admin ?
                        <Recipes recipes={recipes} onDelete={handleDeleteRecipe} onApprove={handleApprove} /> :
                        <Recipes recipes={recipes} />
                }
                <Pagination count={count} page={page} onPageChange={setPage} />
            </div>
        </div>
    )
}