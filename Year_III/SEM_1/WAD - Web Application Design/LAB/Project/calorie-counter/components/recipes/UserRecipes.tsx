import axios from 'axios';
import Loading from 'components/common/Loading';
import Router from 'next/router';
import { useEffect, useState } from 'react';
import { IRecipeSummary } from 'types/recipe';
import Recipes from './Recipes';

interface UserRecipesProps {
    userId: string
}

export default function UserRecipes({ userId }: UserRecipesProps) {
    const [loading, setLoading] = useState(true);
    const [recipes, setRecipes] = useState<IRecipeSummary[]>([]);

    useEffect(() => {
        axios.get('/api/recipes', {
            params: {
                userId: userId
            }
        })
            .then(res => {
                setRecipes(res.data.recipes);
                setLoading(false);
            })
            .catch(err => {
                console.log(err);
                // Router.push('/');
            });
    }, [userId]);

    const handleDelete = async (id: string) => {
        await axios.delete(`/api/recipe/${id}`);
        setRecipes(recipes.filter(recipe => recipe.id !== id));
    }

    return (
        <div className="flex flex-col gap-6 w-full items-center">
            <div className="w-full h-px bg-gray-800"/>
            <div className="text-5xl font-bold font-futura-book">
                Recipes
            </div>
            <div className="w-full h-px bg-gray-800" />
            {loading ?
                <Loading /> :
                <Recipes recipes={recipes} onDelete={handleDelete} editable/>
            }
            <button className="border-8 rounded-3xl border-dashed border-purple-300 p-6 text-3xl w-full font-bold 
                hover:border-solid hover:bg-gray-100 hover:border-purple-400 transition-all duration-500 hover:scale-110"
                onClick={() => Router.push('recipes/create')}
            >
                + Add Recipe
            </button>
        </div>
    )
}