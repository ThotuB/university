import { Minus } from '../../svg/Heroicons'
import Button from '../../common/Button2'

function StepList(props) {
    const { steps, removeStep } = props;

    return (
        <div className="flex flex-col gap-1 rounded-xl bg-purple-200">
            {steps.map((step, index) => (
                <div key={index} className="flex items-center py-1 text-sm font-bold text-gray-600">
                    <Button className="px-3 pl-4"
                            onClick={() => removeStep(index)}>
                        <Minus />
                    </Button>
                    <div className="pl-4">
                        {index + 1}.
                    </div>
                    <div className="w-1/2 px-2">
                        {step.content}
                    </div>
                </div>
            ))}
        </div>
    )
}

export default StepList