import FormCard from "./FormCard"
import FormSection from "./FormField"
import IngredientItem from "./IngredientItem"
import { PlusIcon } from "@heroicons/react/outline"
import { ChangeEvent, useState } from "react"
import Button from 'components/common/Button'
import TextField from "components/common/TextField"
import { Ingredient } from "./Form"

interface RecipeIngredientsProps {
    onSave: (ingredients: Ingredient[]) => void
}

export default function RecipeIngredients({ onSave }: RecipeIngredientsProps) {
    const [ingredient, setIngredient] = useState('')
    const [quantity, setQuantity] = useState('')

    const [ingredients, setIngredients] = useState<Ingredient[]>([] as Ingredient[])

    const handleSave = () => {
        onSave(ingredients)
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
        if (!value.match(/^\d*$/)) return
        setQuantity(value)
    }

    return (
        <FormCard name="Ingredients" description="Enter the ingredients" onSave={handleSave}>
            <FormSection
                label="Add Ingredient"
            >
                <div className="flex gap-2">
                    <Button className="px-3 pl-4 bg-purple-300 hover:ring hover:ring-gray-800"
                        onClick={handleAdd}
                    >
                        <PlusIcon className="w-5" />
                    </Button>
                    <div className="bg-purple-300 p-1 rounded-lg flex gap-2 w-full">
                        <TextField className="py-1"
                            placeholder="Ingredient"
                            maxLength={10}
                            value={ingredient}
                            onChange={changeIngredient}
                        />
                        <TextField className="py-1"
                            placeholder="Quantity"
                            maxLength={5}
                            value={quantity}
                            onChange={changeQuantity}
                        />
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
