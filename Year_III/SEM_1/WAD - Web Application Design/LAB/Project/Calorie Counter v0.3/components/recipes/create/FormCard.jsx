import Button from '../../common/Button'

function FormCard(props) {
    const { name, description } = props;

    function save() {
    }

    return (
        <div className="w-full rounded-2xl flex">
            <div className="w-1/3">
                <div className="font-semibold text-lg">
                    {name}
                </div>
                <div className="text-gray-500">
                    {description}
                </div>
            </div>
            <div className="w-2/3 bg-white border rounded-lg shadow-md overflow-hidden h-full flex flex-col justify-between">
                <div className="p-4 flex flex-col gap-6">
                    {props.children}
                </div>
                <div className="bg-gray-50 px-5 py-3">
                    <div className="float-right">
                        <Button name="Save" 
                            onClick={() => save()}
                        />
                    </div>
                </div>
            </div>
        </div>
    );
}

export default FormCard;