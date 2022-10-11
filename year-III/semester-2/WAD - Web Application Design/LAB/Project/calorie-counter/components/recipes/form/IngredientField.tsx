import FormCard from "./FormCard"
import FormSection from "./FormSection"
import IngredientItem from "./IngredientItem"
import { PlusIcon } from "@heroicons/react/outline"
import { ChangeEvent, useEffect, useState } from "react"
import Button from 'components/common/Button'
import TextField from "components/common/TextField"
import { IRecipeIngredient } from "types/recipe"
import { searchFoods } from "services/food"
import { FoodDto } from "types/food"
import FoodCardSmall from "components/common/food/FoodCardSmall"

interface RecipeIngredientsProps {
    recipeIngredients?: IRecipeIngredient[];
    onSave: (ingredients: IRecipeIngredient[]) => void
}

export default function RecipeIngredients({ recipeIngredients = [], onSave }: RecipeIngredientsProps) {
    const [searchIngredients, setSearchIngredients] = useState<FoodDto[]>([] as FoodDto[])
    const [ingredient, setIngredient] = useState('')
    const [quantity, setQuantity] = useState('')

    const [ingredients, setIngredients] = useState<IRecipeIngredient[]>(recipeIngredients)

    useEffect(() => {
        searchFoods(ingredient, 1)
            .then(res => {
                setSearchIngredients(res.data.foods)
            })
            .catch(err => {
                console.log(err)
            })
    }, [ingredient])

    const handleSave = () => {
        onSave(ingredients)
    }

    const isSaved = () => {
        return ingredients.length === recipeIngredients.length
    }

    const handleAdd = () => {
        if (!ingredient || !quantity) return
        setIngredients([...ingredients, { id: '43', name: ingredient, quantity: quantity }])
        setIngredient('')
        setQuantity('')
    }

    const handleDelete = (index: number) => {
        setIngredients(ingredients.filter((_, i) => i !== index))
    }

    const changeIngredient = ({ target: { value } }: ChangeEvent<HTMLInputElement>) => {
        setIngredient(value)
    }

    const changeQuantity = ({ target: { value } }: ChangeEvent<HTMLInputElement>) => {
        setQuantity(value)
    }

    return (
        <FormCard name="Ingredients" description="Enter the ingredients" saved={isSaved()} onSave={handleSave}>
            <FormSection
                label="Add Ingredient"
            >
                <div className="flex gap-2">
                    <Button className="px-3 pl-4 bg-purple-300 hover:ring hover:ring-gray-800"
                        onClick={handleAdd}
                    >
                        <PlusIcon className="w-5" />
                    </Button>
                    <div className="flex flex-col w-full">
                        <div className="bg-purple-300 p-1 rounded-lg flex gap-2 w-full">
                            <TextField className="py-1"
                                placeholder="Ingredient"
                                value={ingredient}
                                onChange={changeIngredient}
                            />
                            <TextField className="py-1"
                                placeholder="Quantity"
                                value={quantity}
                                onChange={changeQuantity}
                            />
                        </div>
                        {/* <div className="">
                            <div className="bg-white px-2 absolute flex flex-col divide-y mt-2 z-50 border-4 border-purple-300 rounded-lg">
                                {searchIngredients.map((food, index) => (
                                    <FoodCardSmall key={index} food={food}/>
                                ))}
                            </div>
                        </div> */}
                    </div>
                </div>
                <div className="flex flex-col gap-1">
                    {ingredients.map((ingredient, index) => (
                        <IngredientItem key={index} ingredient={ingredient} onDelete={() => handleDelete(index)} />
                    ))}
                </div>
            </FormSection>
        </FormCard>
    )
}
