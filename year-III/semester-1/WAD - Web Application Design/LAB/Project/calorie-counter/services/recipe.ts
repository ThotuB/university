import axios, { AxiosResponse } from "axios";
import { RecipeDto, RecipesDto } from "types/recipe";

export const postRecipe = (recipe: RecipeDto) => {
    const url = `/api/recipes`;
    
    return axios.post(url, recipe);
}

export const getRecipe = (id: string): Promise<AxiosResponse<RecipeDto>> => {
    const url = `/api/recipe/${id}`;
    
    return axios.get(url);
}

export const deleteRecipe = (id: string) => {
    const url = `/api/recipe/${id}`;
    
    return axios.delete(url);
}

export const updateRecipe = (recipe: RecipeDto) => {
    const url = `/api/recipe/${recipe.id}`;
    
    return axios.put(url, recipe);
}

export const getRecipes = (page: number = 1, pageSize: number = 10, userId: string | null = null): Promise<AxiosResponse<RecipesDto>> => {
    const url = `/api/recipes`
    const query = {
        params: {
            pageNumber: page,
            pageSize: pageSize,
            userId: userId
        }
    }

    return axios.get(url, query)
}