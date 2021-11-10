import RecipeInfo from "./RecipeInfo";
import RecipeIngredients from "./RecipeIngredients";
import RecipeSteps from "./RecipeSteps";

import Button from "../../common/Button";
import { useState } from "react";

function RecipesForm(props) {
    const [extend, setExtend] = useState(false);

    return (
        <div className="w-full bg-gray-100 rounded-md border p-4 flex flex-col gap-6">
            <RecipeInfo />

            <hr className="border-gray-200 border-2 rounded-full" />

            <RecipeIngredients />

            <hr className="border-gray-200 border-2 rounded-full" />

            <RecipeSteps />

            <hr className="border-gray-200 border-2 rounded-full" />

            <Button>SHOW MORE</Button>
        </div>
    );
}

export default RecipesForm;
