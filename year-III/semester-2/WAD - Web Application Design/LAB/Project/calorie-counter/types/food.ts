export interface FoodsDto {
    foods: FoodDto[];
    totalHits: number;
    totalPages: number;
    currentPage: number;
}

export interface FoodDto {
    fdcId: number;
    description: string;
    brandName: string;
    brandOwner: string;
    foodNutrients: NutrientDto[];
    servingSize: number;
    servingSizeUnit: string;
    ingredients: string;
    foodCategory: string;
    packageWeight: string;
}

export interface NutrientDto {
    nutrientId: number;
    nutrientName: string;
    nutrientNumber: string;
    unitName: string;
    value: number;
}