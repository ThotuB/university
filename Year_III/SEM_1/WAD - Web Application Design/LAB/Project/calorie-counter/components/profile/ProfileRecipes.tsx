import Loading from 'components/common/Loading';
import { useUser } from 'contexts/UserContext';
import Router from 'next/router';
import { useEffect, useState } from 'react';
import { deleteRecipe, getRecipes } from 'services/recipe';
import { RecipesDto, RecipeSummaryDto } from 'types/recipe';
import Recipes from '../recipes/RecipeGrid';

interface UserRecipesProps {
    userId: string;
    isUser?: boolean
}

export default function UserRecipes({ userId, isUser }: UserRecipesProps) {
    const [loading, setLoading] = useState(true);
    const [recipes, setRecipes] = useState<RecipeSummaryDto[]>([]);

    useEffect(() => {
        getRecipes(1, 10, userId)
            .then(res => {
                setRecipes(res.data.recipes);
                setLoading(false);
            })
            .catch(err => {
                console.log(err);
            });
    }, [userId]);

    const handleDelete = async (id: string) => {
        await deleteRecipe(id)
        setRecipes(recipes.filter(recipe => recipe.id !== id));
    }

    return (
        <div className="flex flex-col gap-6 w-full items-center">
            {loading ?
                <Loading /> :
                isUser ? 
                    <Recipes recipes={recipes} onDelete={handleDelete} editable/> :
                    <Recipes recipes={recipes} />
            }
        </div>
    )
}