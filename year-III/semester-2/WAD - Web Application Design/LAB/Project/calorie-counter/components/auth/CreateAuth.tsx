import Button from 'components/common/Button'
import TextField from 'components/common/TextField'
import { useState } from 'react'
import { EyeIcon, EyeOffIcon } from '@heroicons/react/outline'
import { useUser } from 'contexts/UserContext'
import { Error, defaultError, validateConfirmPassword, validateEmail, validatePassword, validateUsername } from '../../utils/validation'
import Router from 'next/router'
import { getAuth } from 'firebase/auth'
import { updateUserProfile } from 'services/user'
import { createProfile } from 'utils/profile'

export default function CreateAuth() {
    const [username, setUsername] = useState('')
    const [email, setEmail] = useState('')
    const [password, setPassword] = useState('')
    const [confirmPassword, setConfirmPassword] = useState('')

    const [usernameError, setUsernameError] = useState<Error>(defaultError)
    const [emailError, setEmailError] = useState<Error>(defaultError)
    const [passwordError, setPasswordError] = useState<Error>(defaultError)
    const [confirmPasswordError, setConfirmPasswordError] = useState<Error>(defaultError)

    const [showPassword, setShowPassword] = useState(false)
    const [loading, setLoading] = useState(false)

    const { signUp, update } = useUser()

    const validate = () => {
        let isValid = validateUsername(username, setUsernameError)
        isValid = validateEmail(email, setEmailError) && isValid
        isValid = validatePassword(password, setPasswordError) && isValid
        isValid = validateConfirmPassword(confirmPassword, password, setConfirmPasswordError) && isValid

        return isValid
    }

    const handleCreate = async () => {
        if (!validate()) return

        setLoading(true)

        try {
            await signUp(email, password)

            const user = getAuth().currentUser

            await update(user, username)
            await createProfile(user)
            Router.push('/home')
        }
        catch (error) {
            console.error(error)
        }

        setLoading(false)
    }

    return (
        <form className="mt-6 flex flex-col gap-4"
            autoComplete="off"
            onSubmit={e => e.preventDefault()}
        >
            <TextField label='Username' type="text"
                value={username}
                onChange={(event) => setUsername(event.target.value)}
                maxLength={20}
                required
                error={usernameError.error}
                errorText={usernameError.message}
            />
            <TextField label='Email' type="text"
                value={email}
                onChange={(event) => setEmail(event.target.value)}
                maxLength={50}
                required
                error={emailError.error}
                errorText={emailError.message}
            />
            <div className='flex gap-2'>
                <TextField label='Password' type={showPassword ? 'text' : 'password'}
                    value={password}
                    onChange={(event) => setPassword(event.target.value)}
                    maxLength={20}
                    required
                    error={passwordError.error}
                    errorText={passwordError.message}
                />
                <button onClick={() => setShowPassword(!showPassword)}>
                    {showPassword ? <EyeIcon className="w-6 pt-7" /> : <EyeOffIcon className="w-6 pt-7" />}
                </button>
            </div>
            <TextField label='Confirm Password' type="password"
                value={confirmPassword}
                onChange={(event) => setConfirmPassword(event.target.value)}
                maxLength={20}
                required
                error={confirmPasswordError.error}
                errorText={confirmPasswordError.message}
            />

            {loading ?
                <div className='px-3 py-2 font-bold rounded-md text-white bg-gray-600 text-center'>
                    Create Account
                </div> :
                <Button onClick={handleCreate}>
                    Create Account
                </Button>
            }
        </form>
    )
}