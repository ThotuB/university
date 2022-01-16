export interface IRecipe {
    id: string;
    name: string;
    description: string;
    image: string;
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

export interface IRecipeSummary {
    id: string;
    name: string;
    description: string;
    image: string;
    date: string;
    tags?: string[];
    user : {
        id: string;
        name: string;
        image: string;
    }
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
