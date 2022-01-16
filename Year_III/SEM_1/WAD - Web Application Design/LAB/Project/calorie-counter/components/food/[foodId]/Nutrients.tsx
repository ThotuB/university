import Button from 'components/common/Button'
import Toggle from 'components/common/Toggle'
import { useState, useEffect } from 'react'
import NutrientTable from './NutrientTable'
import { NutrientProps } from './NutrientTable'
import { PlusIcon } from '@heroicons/react/outline'

export interface Nutrient {
    foodNutrients: NutrientProps[],
    description: string
    brandName: string
    brandOwner: string
    servingSize: number
    servingSizeUnit: string
    ingredients: string
}

interface NutrientsProps {
    food: Nutrient
}

export default function Nutrients({ food: { foodNutrients, description, brandName, brandOwner, servingSize, servingSizeUnit, ingredients } }: NutrientsProps) {
    const [inputPortion, setInputPortion] = useState(0)
    const [selected, setSelected] = useState('100')
    const [ratio, setRatio] = useState(1)

    const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const value = parseInt(e.target.value)
        if (value && value > 0) {
            setInputPortion(value)
        }
        else {
            setInputPortion(0)
        }
    }

    const handleAdd = () => {

    }

    useEffect(() => {
        switch (selected) {
            case '100':
                setRatio(1)
                break
            case 'serving':
                setRatio(servingSize / 100)
                break
            case 'input':
                setRatio(inputPortion / 100)
                break
        }
    }, [selected, inputPortion])

    return (
        <div className="flex flex-col w-full max-w-5xl gap-6 border-2 rounded-2xl p-4 bg-white">
            <div className="flex flex-col items-center">
                <div className="text-6xl font-bold">
                    {description}
                </div>
                <div className="italic">
                    {brandOwner}
                </div>
            </div>
            <div className="flex justify-between">
                <div className="flex gap-4 items-center">
                    <div className="text-xl">
                        Portion:
                    </div>
                    <Toggle.Group
                        value={selected}
                        onChange={setSelected}
                    >
                        <Toggle.Button value="100">
                            100 {servingSizeUnit}
                        </Toggle.Button>
                        <Toggle.Button value="serving">
                            {servingSize} {servingSizeUnit}
                        </Toggle.Button>
                        <Toggle.Button value="input">
                            <input type='number' className='w-16 mr-2 bg-transparent text-right'
                                value={inputPortion}
                                onChange={handleInputChange}
                            />
                            {servingSizeUnit}
                        </Toggle.Button>
                    </Toggle.Group>
                </div>
                <Button className='flex gap-3' onClick={handleAdd}>
                    <PlusIcon className='w-6' /> Add Food
                </Button>
            </div>
            <NutrientTable nutrients={foodNutrients} ratio={ratio} />
            <div className="">
                INGREDIENTS: {ingredients}
            </div>
        </div>
    )
}