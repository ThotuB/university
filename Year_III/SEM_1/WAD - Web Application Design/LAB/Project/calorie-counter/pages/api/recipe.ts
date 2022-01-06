import { MongoClient } from 'mongodb';
import { NextApiRequest, NextApiResponse } from 'next';

type Data = {
    message: string;
}

export default async function handler(req: NextApiRequest, res: NextApiResponse<Data>) {
    if (req.method === 'POST') {
        const data = req.body;

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/recipes?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('recipes');

        const result = await collection.insertOne(data)

        console.log(result)

        client.close()

        res.status(201).json({
            message: 'Recipe added',
        })
    }
}
