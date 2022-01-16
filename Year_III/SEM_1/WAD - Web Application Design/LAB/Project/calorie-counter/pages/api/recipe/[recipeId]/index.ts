import { MongoClient, ObjectId } from 'mongodb';
import { NextApiRequest, NextApiResponse } from 'next';
import { IRecipe } from 'types/recipe';

type GetData = IRecipe
type DeleteData = {
    message: string
}

export default async function handler(req: NextApiRequest, res: NextApiResponse<GetData | DeleteData>) {
    if (req.method === 'GET') {
        const { recipeId } = req.query;

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/recipes?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('recipes');

        const result = await collection.findOne({ _id: new ObjectId(recipeId as string) });

        client.close()

        if (!result) {
            res.status(404);
            return;
        }

        res.status(200).json({
            id: result._id.toString(),
            name: result.name,
            description: result.description,
            image: result.image,
            ingredients: result.ingredients,
            steps: result.steps,
            user: {
                id: result.user.userId,
                name: result.user.name,
                image: result.user.image
            }
        })
    }

    if (req.method === 'DELETE') {
        const { recipeId } = req.query;

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/recipes?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('recipes');

        const result = await collection.deleteOne({ _id: new ObjectId(recipeId as string) });

        client.close()

        if (!result) {
            res.status(404);
            return;
        }

        res.status(200).json({
            message: 'Recipe deleted successfully'
        })
    }
}
