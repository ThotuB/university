import FormCard from "./FormCard"
import FormSection from "./FormSection"
import IngredientList from "./IngredientList"
import { Plus } from '../../svg/Heroicons'
import { useState } from "react"
import Button from '../../common/Button2'
import Select from '../../common/Select'

const unitOptions = [
    {value: 'mg', label: 'mg'},
    {value: 'g', label: 'g'},
    {value: 'kg', label: 'kg'},
    {value: 'ml', label: 'ml'},
    {value: 'l', label: 'l'},
    {value: 'unit', label: 'unit'},
]

const selectStyles = {
    container: (base, state) => ({
      ...base,
      zIndex: "999"
    })
  };

function RecipeIngredients() {
    const [ingredient, setIngredient] = useState('')
    const [quantity, setQuantity] = useState('')
    const [unit, setUnit] = useState('unit')

    const [ingredients, setIngredients] = useState([])

    const changeQuantity = (value) => {
        if (value.length > 3) return
        for (let i = 0; i < value.length; i++) {
            if (value[i] < '0' || value[i] > '9') {
                return
            }
        }
        setQuantity(value)
    }

    const changeIngredient = (value) => {
        if (value.length > 30) return
        for (let i = 0; i < value.length; i++) {
            if (value[i] < 'a' || value[i] > 'z') {
                return
            }
        }
        setIngredient(value)
    }

    const addIngredient = () => {
        if (ingredient === '' || quantity === '') return
        const newIngredient = {name: ingredient, quantity: quantity, unit: unit}
        setIngredients([...ingredients, newIngredient])
        setIngredient('')
        setQuantity('')
    }

    const removeIngredient = (index) => {
        setIngredients(ingredients.filter((ingredient, i) => i !== index))
    }

    return (
        <FormCard name="Ingredients" description="Enter the ingredients">
            <FormSection>
                Add Ingredient *
                <div className="flex gap-2">
                    <Button className="px-3 pl-4 bg-purple-300 hover:ring hover:ring-gray-800"
                            onClick={() => addIngredient()}>
                        <Plus />
                    </Button>
                    <div className="bg-purple-300 p-1 rounded-lg flex gap-2 w-full">
                        <input className="w-1/2 rounded-l-md py-1 px-3 outline-none ring-purple-500 focus:ring-4"
                                placeholder="Ingredient"
                                value={ingredient}
                                onChange={(e) => changeIngredient(e.target.value)}/>
                        <input className="w-1/3 py-1 px-3 outline-none ring-purple-500 focus:ring-4"
                                placeholder="Quantity"
                                value={quantity}
                                onChange={(e) => changeQuantity(e.target.value)}/>
                        <Select className="w-1/6 outline-none flex flex-col ring-purple-500 focus:ring-4"
                                options={unitOptions} value={unit} onChange={(e) => setUnit(e.target.value)} placeholder=''/>
                    </div>
                </div>
                <IngredientList ingredients={ingredients} removeIngredient={removeIngredient} />
            </FormSection>
        </FormCard>
    )
}

export default RecipeIngredients
