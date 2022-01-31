export interface RecipeDto {
    id: string;
    name: string;
    description: string;
    image: string;
    approved?: boolean;
    ingredients: {
        id: string;
        name: string;
        quantity: string;
    }[]
    steps: string[];
    user: {
        id: string;
        name: string;
        image: string;
    }
}

export interface RecipeSummaryDto {
    id: string;
    name: string;
    description: string;
    image: string;
    date: string;
    tags?: string[];
    approved?: boolean;
    user : {
        id: string;
        name: string;
        image: string;
    }
}

export interface RecipesDto {
    recipes: RecipeSummaryDto[];
    entries: number;
    pages: number;
}

export interface IRecipeInfo {
    name: string;
    description: string;
    image: string;
}

export interface IRecipeIngredient {
    id: string;
    name: string;
    quantity: string;
}
