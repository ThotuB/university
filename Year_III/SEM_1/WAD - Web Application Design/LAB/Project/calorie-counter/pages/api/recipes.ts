import { MongoClient } from 'mongodb';
import { NextApiRequest, NextApiResponse } from 'next';

type Data = {
    id: string;
    name: string;
    description: string;
}

export default async function handler(req: NextApiRequest, res: NextApiResponse<Data[]>) {
    if (req.method === 'GET') {
        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/recipes?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('recipes');

        const result = await collection.find().toArray();

        console.log('get')

        client.close()

        res.status(200).json(
            result.map(recipe => ({
                id: recipe._id.toString(),
                name: recipe.name,
                description: recipe.description,
            }))
        )
    }
}
