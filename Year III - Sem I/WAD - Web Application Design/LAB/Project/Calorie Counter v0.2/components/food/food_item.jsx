import Card from '../ui/card';
import Link from 'next/link';

function FoodItem(props) {
    const { id, name, calories, company, author } = props;

    return (
        <Card>
            <div className="">
                <div className="">
                    {name}
                </div>
                <div className="">
                    {calories + " kcal"}
                </div>
                <div className="">
                    {company}
                </div>
                <div className="">
                    {"by " + author}
                </div>
                <div className="">
                    <Link href="/food/[id]" as={`/food/${id}`}>
                        Details
                    </Link>
                </div>
            </div>
        </Card>
    );
}

export default FoodItem;